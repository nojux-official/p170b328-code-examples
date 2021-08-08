using System.Linq;
using System.Threading;

namespace MailboxCS
{
    public class MailBox
    {
        private int _letter;
        private readonly int _readers;
        private bool _canWrite;
        private bool[] _canRead;
        private readonly object _locker;

        public MailBox(int readers)
        {
            _readers = readers;
            _canRead = Enumerable.Repeat(false, readers).ToArray();
            _letter = 0;
            _canWrite = true;
            _locker = new object();
        }

        public void Put(int newLetter)
        {
            lock (_locker)
            {
                while (!_canWrite)
                {
                    Monitor.Wait(_locker);
                }

                _letter = newLetter;
                _canWrite = false;
                _canRead = Enumerable.Repeat(true, _readers).ToArray();
                Monitor.PulseAll(_locker);
            }
        }

        public int Get(int k)
        {
            int newLetter;
            lock (_locker)
            {
                while (!_canRead[k])
                {
                    Monitor.Wait(_locker);
                }

                newLetter = _letter;
                _canRead[k] = false;
                _canWrite = _canRead.All(c => !c);
                Monitor.PulseAll(_locker);
            }
            return newLetter;
        }
    }
}