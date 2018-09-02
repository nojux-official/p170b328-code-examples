using System.Threading;

namespace ElementariPrograma
{
    internal class Program
    {
        public static void Main(string[] args)
        {
            var executor1 = new Executor("Pirma");
            var executor2 = new Executor("Antra");
            var thread1 = new Thread(executor1.Execute);
            var thread2 = new Thread(executor2.Execute);
            thread1.Start();
            thread2.Start();
            thread1.Join();
            thread2.Join();
        }
    }
}