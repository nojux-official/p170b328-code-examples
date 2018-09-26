using System;
using System.Linq;
using System.Threading;

namespace mailbox_cs
{
    internal static class Program
    {
        public static void Main(string[] args)
        {
            const int readerCount = 5;
            const int itemsProcessed = 6;
            var mailbox = new MailBox(readerCount);
            var readers = Enumerable.Range(0, readerCount).Select(i => new Reader(itemsProcessed, mailbox, i)).ToList();
            var threads = readers.Select(reader => new Thread(reader.Read)).ToList();
            threads.Add(new Thread(() =>
            {
                for (var i = 0; i < itemsProcessed; i++)
                {
                    mailbox.Put(i * i);
                }
            }));
            foreach (var thread in threads)
            {
                thread.Start();
            }

            foreach (var thread in threads)
            {
                thread.Join();
            }

            var lines = readers.Select(r => r.Letters).Select(letters => string.Join(", ", letters));
            foreach (var line in lines)
            {
                Console.WriteLine(line);
            }
        }
    }
}
