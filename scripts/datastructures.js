// Linked List Implementation
class Node {
  constructor(book) {
    this.book = book;
    this.next = null;
  }
}

class LinkedList {
  constructor() {
    this.head = null;
  }

  add(book) {
    const newNode = new Node(book);
    newNode.next = this.head;
    this.head = newNode;
  }

  remove(isbn) {
    let current = this.head;
    let prev = null;

    while (current !== null) {
      if (current.book.isbn === isbn) {
        if (prev === null) {
          this.head = current.next;
        } else {
          prev.next = current.next;
        }
        return;
      }
      prev = current;
      current = current.next;
    }
  }

  findByTitle(title) {
    let current = this.head;

    while (current !== null) {
      if (current.book.title === title) {
        return current.book;
      }
      current = current.next;
    }
    return null;
  }
}

// Hash Table Implementation
class HashTable {
  constructor(size = 101) {
    this.table = new Array(size);
  }

  _hash(key) {
    return (
      key.split("").reduce((acc, char) => acc + char.charCodeAt(0), 0) %
      this.table.length
    );
  }

  insert(isbn, book) {
    const index = this._hash(isbn);
    if (!this.table[index]) {
      this.table[index] = [];
    }
    this.table[index].push({ isbn, book });
  }

  get(isbn) {
    const index = this._hash(isbn);
    const bucket = this.table[index];
    if (bucket) {
      for (const entry of bucket) {
        if (entry.isbn === isbn) {
          return entry.book;
        }
      }
    }
    return null;
  }

  remove(isbn) {
    const index = this._hash(isbn);
    const bucket = this.table[index];
    if (bucket) {
      this.table[index] = bucket.filter((entry) => entry.isbn !== isbn);
    }
  }
}

// Queue Implementation
class Queue {
  constructor() {
    this.items = [];
  }

  enqueue(user) {
    this.items.push(user);
  }

  dequeue() {
    return this.items.shift();
  }

  peek() {
    return this.items[0];
  }

  isEmpty() {
    return this.items.length === 0;
  }
}

// Export Classes
export { LinkedList, HashTable, Queue };
