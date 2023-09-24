using System;
using System.Linq;
using System.Threading;

namespace MailboxCS
{
    public class MailBox
    {
        private readonly object _locker;
        private bool _canWrite;
        private bool[] _canRead;
        private const int EmptyMessage = int.MinValue;
        private int _letter = EmptyMessage;

        public MailBox(int readers)
        {
            _canRead = new bool[readers];
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
                Array.Fill(_canRead, true);
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
                _canWrite = !_canRead.Any(r => r);
                Monitor.PulseAll(_locker);
            }
            return newLetter;
        }
    }
}