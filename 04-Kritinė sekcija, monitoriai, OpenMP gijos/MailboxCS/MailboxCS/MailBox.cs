using System;
using System.Linq;
using System.Threading;

namespace MailboxCS
{
    public class MailBox
    {
        private readonly object _locker;
        private bool _canWrite;
        private readonly bool[] _canRead;
        private const int EmptyMessage = int.MinValue;
        private int _letter = EmptyMessage;

        public MailBox(int readers)
        {
            _canRead = new bool[readers];
            _canWrite = true;
            _locker = new object();
        }

        /// <summary>
        /// Adds a message to the mailbox overwriting the existing message. If the previous message has not been
        /// retrieved by a Get call by each reader, the caller is blocked.
        /// </summary>
        /// <param name="newLetter">The value to add to the mailbox</param>
        public void Put(int newLetter)
        {
            // this method modifies _letter, _canWrite and _canRead attributes, which are also used by reader threads,
            // therefore a lock is required for this method
            lock (_locker)
            {
                while (!_canWrite)
                {
                    // _canWrite flag indicates whether the Put method can safely add the message or not. If not, the
                    // thread must be blocked so that it waits for the flag to change.
                    Monitor.Wait(_locker);
                }

                // write the message
                _letter = newLetter;
                // a new message has been added, the next message cannot be added immediately - all reader threads must
                // read it first
                _canWrite = false;
                // all reader threads may now ready the message, update all _canRead values to true
                Array.Fill(_canRead, true);
                // if any reader threads were block by calling Wait in Get method, notify them here
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