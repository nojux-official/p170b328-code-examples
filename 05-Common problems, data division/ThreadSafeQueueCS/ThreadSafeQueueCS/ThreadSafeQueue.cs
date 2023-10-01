using System.Collections.Generic;

namespace ThreadSafeQueueCS
{
    public class ThreadSafeQueue<T>
    {
        private readonly Queue<T> _queue = new Queue<T>();

        public void AddItem(T item)
        {
            lock (this)
            {
                _queue.Enqueue(item);
            }
        }

        public T PopItem()
        {
            lock (this)
            {
                return _queue.Dequeue();
            }
        }

        public int ItemCount
        {
            get
            {
                lock (this)
                {
                    return _queue.Count;
                }
            }
        }
    }
}