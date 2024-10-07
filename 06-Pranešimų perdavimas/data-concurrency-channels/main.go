package main

import (
	"fmt"
	"io"
	"net/http"
	"regexp"
)

const crawlerCount = 4
const analyserCount = 4
const analyzerStopMessage = "<die>"

func main() {
	urlChannel := make(chan string)
	contentChannel := make(chan string)
	titleChannel := make(chan string)

	coordinatorToMain := make(chan bool)
	crawlerToCoordinator := make(chan bool)
	coordinatorToPrinter := make(chan bool)
	urls := [4]string{"https://www.google.com", "https://duckduckgo.com/", "https://www.bing.com", "https://yahoo.com"}

	// information flows like this: main thread [url] -> crawler [content] -> title extractor [title] -> printer.
	// crawler also has to analyse downloaded HTML to extract the links

	for i := 0; i < crawlerCount; i++ {
		// crawler process
		// gets URLs via channel, downloads their content, sends their content for analysis to title extracting
		// processes; each content is parsed, their links extracted, link content downloaded and passed to title
		// extractors
		go func() {
			for {
				url := <-urlChannel
				if url == "" {
					crawlerToCoordinator <- true
					break
				}
				content := getWebpageContent(url)
				contentChannel <- content
				for _, link := range analyzeWebContent(content) {
					linkContent := getWebpageContent(link)
					contentChannel <- linkContent
				}
			}
		}()
	}

	for i := 0; i < analyserCount; i++ {
		// analyser process
		// accepts webpage content and extracts title from it. The title is passed to printer process
		go func() {
			for {
				content := <-contentChannel
				title := extractWebpageTitle(content)
				if title == analyzerStopMessage {
					break
				}
				if len(title) > 0 {
					titleChannel <- title
				}
			}
		}()
	}

	go func() {
		// coordinator process
		// waits for an end-of-work signal from all crawlers...
		for i := 0; i < crawlerCount; i++ {
			<-crawlerToCoordinator
		}
		// sends an end-of-work signal to all analysers...
		for i := 0; i < analyserCount; i++ {
			contentChannel <- analyzerStopMessage
		}
		// sends an end-of-work signal to printer and main process
		coordinatorToPrinter <- true
		coordinatorToMain <- true
	}()

	go func() {
		// printer process
		// waits for messages from 2 channels
		for {
			select {
			// prints received title
			case title := <-titleChannel:
				fmt.Println(title)
				break
			case <-coordinatorToPrinter:
				// end-of-work signal
				return
			}
		}
	}()

	// send all data to crawlers
	for _, url := range urls {
		urlChannel <- url
	}
	// send end-of-work signal to each crawler
	for i := 0; i < crawlerCount; i++ {
		urlChannel <- ""
	}
	// wait for signal from coordinator
	<-coordinatorToMain
}

const regexLink = `href=['"]?([^'" >]+)['"]`
const regexTitle = `<title.*?>(.*)</title>`

// gets the content of a webpage under the specified url as a string
func getWebpageContent(url string) string {
	resp, err := http.Get(url)
	if err != nil {
		return ""
	}
	body, err := io.ReadAll(resp.Body)
	if err != nil {
		return ""
	}
	_ = resp.Body.Close()
	return string(body)
}

func extractWebpageTitle(textPage string) string {
	titleRegexp := regexp.MustCompile(regexTitle)
	title := titleRegexp.FindStringSubmatch(textPage)
	if len(title) == 2 {
		return title[1]
	}
	return ""
}

func analyzeWebContent(text string) []string {
	result := make([]string, 0)
	linkRegex := regexp.MustCompile(regexLink)
	for _, match := range linkRegex.FindAllStringSubmatch(text, -1) {
		result = append(result, match[1])
	}
	return result
}
