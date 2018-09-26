using System.Collections.Generic;

namespace mailbox_cs
{
    public class Reader
    {
        private readonly int _itemsToRead;
        public List<int> Letters { get; }
        private readonly MailBox _mailbox;
        private readonly int _id;

        public Reader(int itemsToRead, MailBox mailbox, int id)
        {
            _itemsToRead = itemsToRead;
            _mailbox = mailbox;
            _id = id;
            Letters = new List<int>();
        }

        public void Read()
        {
            for (var i = 0; i < _itemsToRead; i++)
            {
                Letters.Add(_mailbox.Get(_id));
            }
        }
    }
}
