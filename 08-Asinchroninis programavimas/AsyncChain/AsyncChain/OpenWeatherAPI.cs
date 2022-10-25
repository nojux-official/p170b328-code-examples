using System.IO;
using System.Net.Http;
using System.Text.Json;
using System.Threading.Tasks;

namespace AsyncChain
{
    /// <summary>
    /// A class that encapsulates communication with OpenWeather service
    /// </summary>
    public class OpenWeatherApi
    {
        private readonly string _apiKey;

        public OpenWeatherApi()
        {
            // sets API key from api_key.txt file. One should register for the key at OpenWeather web page
            _apiKey = File.ReadAllText("api_key.txt");
        }

        /// <summary>
        /// Makes a request to download current temperature for a city
        /// </summary>
        /// <param name="cityId">ID of the city to get temperature for</param>
        /// <returns>JSON returned by OpenWeather</returns>
        private async Task<Stream> MakeOpenWeatherRequest(int cityId)
        {
            // url should look like this: http://api.openweathermap.org/data/2.5/weather?id=<cityId>&appid=<apiKey>
            const string apiRoot = "http://api.openweathermap.org/";
            using var client = new HttpClient();
            return await client.GetStreamAsync($"{apiRoot}data/2.5/weather?id={cityId}&appid={_apiKey}");
        }

        /// <summary>
        /// Given the full JSON response from OpenWeather API, extract temperature as a double
        /// </summary>
        /// <param name="jsonResponse">full response retrieved from OpenWeather API</param>
        /// <returns>current temperature</returns>
        private async Task<double> ParseResponse(Stream jsonResponse)
        {
            var jsonObject = await JsonDocument.ParseAsync(jsonResponse);
            var root = jsonObject.RootElement;
            var main = root.GetProperty("main");
            return main.GetProperty("temp").GetDouble();
        }
        
        /// <summary>
        /// Convert kelvins to degrees Celsius
        /// </summary>
        /// <param name="kelvins">temperature in kelvins</param>
        /// <returns>temperature in Celsius</returns>
        private double KelvinToCelsius(double kelvins)
        {
            return kelvins - 273.15;
        }

        public async Task<double> GetTemperatureAsync(int cityId)
        {
            var jsonStream = await MakeOpenWeatherRequest(cityId);
            var temperatureInKelvins = await ParseResponse(jsonStream);
            return KelvinToCelsius(temperatureInKelvins);
        }
    }
}