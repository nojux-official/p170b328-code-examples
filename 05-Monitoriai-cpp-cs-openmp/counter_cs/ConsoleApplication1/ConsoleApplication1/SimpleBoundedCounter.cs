using System.Threading;

namespace ConsoleApplication1
{
    public class SimpleBoundedCounter
    {
        private const long Min = 0;
        private const long Max = 50;
        private long _count;

        public long Count
        {
            get => _count;
            private set
            {
                _count = value;
                Monitor.PulseAll(_locker);
            }
        }

        private readonly object _locker;

        public SimpleBoundedCounter()
        {
            _count = Min;
            _locker = new object();
        }

        public void Increase()
        {
            lock (_locker)
            {
                while (Count == Max)
                {
                    Monitor.Wait(_locker);
                }
                Count = Count + 1;
            }
        }

        public void Decrease()
        {
            lock (_locker)
            {
                while (Count == 0)
                {
                    Monitor.Wait(_locker);
                }

                Count = Count - 1;
            }
        }
    }
}
