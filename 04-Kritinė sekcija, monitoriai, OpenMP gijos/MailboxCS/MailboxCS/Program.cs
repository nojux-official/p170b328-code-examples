using System;
using System.Linq;
using System.Threading;

namespace MailboxCS
{
    internal static class Program
    {
        private const int TerminateMessage = int.MinValue;
        /// <summary>
        /// The program implements a broadcast pattern. One sender thread sends messages, many receivers receive the
        /// message. All receivers must read the message before the next message is sent.
        /// </summary>
        private static void Main()
        {
            const int readerCount = 5;
            var mailbox = new MailBox(readerCount);
            // create the reader objects and pass their Read methods to threads
            var readers = Enumerable.Range(0, readerCount)
                .Select(i => new Reader(TerminateMessage, mailbox, i))
                .ToList();
            var threads = readers.Select(reader => new Thread(reader.Read)).ToList();
            foreach (var thread in threads)
            {
                thread.Start();
            }
            // main thread acts as the writer thread, write 6 messages
            for (var i = 0; i < 6; i++)
            {
                mailbox.Put(i * i);
            }
            // write the termination message
            mailbox.Put(TerminateMessage);
            
            // wait for readers to finish
            foreach (var thread in threads)
            {
                thread.Join();
            }

            // construct an enumerable where one item is all received messages from one reader as a string
            var lines = readers.Select(r => string.Join(", ", r.Letters));
            // expected output - 6 identical lines: "0, 1, 4, 9, 16, 25"
            foreach (var line in lines)
            {
                Console.WriteLine(line);
            }
        }
    }
}