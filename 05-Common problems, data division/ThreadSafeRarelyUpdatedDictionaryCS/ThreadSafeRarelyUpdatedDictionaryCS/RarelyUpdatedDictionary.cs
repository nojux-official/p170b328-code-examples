using System.Collections.Generic;
using System.Threading;

namespace ThreadSafeRarelyUpdatedDictionaryCS
{
    public class RarelyUpdatedDictionary<TK, TV>
    {
        private readonly Dictionary<TK, TV> _storage = new Dictionary<TK, TV>();
        private readonly ReaderWriterLockSlim _lock = new ReaderWriterLockSlim();

        public TV this[TK key]
        {
            get
            {
                _lock.EnterReadLock();
                try
                {
                    return _storage[key];
                }
                finally
                {
                    _lock.ExitReadLock();
                }
            }
            set
            {
                _lock.EnterWriteLock();
                try
                {
                    _storage[key] = value;
                }
                finally
                {
                    _lock.ExitWriteLock();
                }
            }
        }
    }
}