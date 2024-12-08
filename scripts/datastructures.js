// Node for Linked List
class Node {
  constructor(book) {
    this.book = book; // The book data to be stored in this node
    this.next = null; // Pointer to the next node in the list
  }
}

// Linked List Implementation
class LinkedList {
  constructor() {
    this.head = null; // Points to the first node in the linked list
  }

  // Adds a new book to the beginning of the linked list
  add(book) {
    const newNode = new Node(book); // Create a new node with the given book
    newNode.next = this.head; // Point the new node to the current head
    this.head = newNode; // Update the head to be the new node
  }

  // Removes a book from the linked list by its ISBN
  remove(isbn) {
    let current = this.head; // Start at the head of the list
    let prev = null; // Pointer to the previous node

    while (current !== null) {
      if (current.book.isbn === isbn) {
        // Check if the ISBN matches
        if (prev === null) {
          this.head = current.next; // Update head if the first node is removed
        } else {
          prev.next = current.next; // Update the previous node's pointer
        }
        return; // Exit after removal
      }
      prev = current; // Move the previous pointer to the current node
      current = current.next; // Move to the next node
    }
  }

  // Finds and returns a book by its title
  findByTitle(title) {
    let current = this.head; // Start at the head of the list

    while (current !== null) {
      if (current.book.title === title) {
        // Check if the title matches
        return current.book; // Return the book if found
      }
      current = current.next; // Move to the next node
    }
    return null; // Return null if no book with the given title is found
  }
}

// Hash Table Implementation
class HashTable {
  constructor(size = 101) {
    this.table = new Array(size); // Create an array to store the entries
  }

  // Hash function to generate an index for the key (ISBN)
  _hash(key) {
    return (
      key.split("").reduce((acc, char) => acc + char.charCodeAt(0), 0) %
      this.table.length
    );
  }

  // Insert a book into the hash table using its ISBN as the key
  insert(isbn, book) {
    const index = this._hash(isbn); // Get the index for the ISBN
    if (!this.table[index]) {
      this.table[index] = []; // Create a new bucket if it doesn't exist
    }
    this.table[index].push({ isbn, book }); // Insert the book in the bucket
  }

  // Get a book from the hash table by its ISBN
  get(isbn) {
    const index = this._hash(isbn); // Get the index for the ISBN
    const bucket = this.table[index]; // Get the bucket at the index
    if (bucket) {
      for (const entry of bucket) {
        if (entry.isbn === isbn) {
          return entry.book; // Return the book if found
        }
      }
    }
    return null; // Return null if the book is not found
  }

  // Remove a book from the hash table using its ISBN
  remove(isbn) {
    const index = this._hash(isbn); // Get the index for the ISBN
    const bucket = this.table[index]; // Get the bucket at the index
    if (bucket) {
      this.table[index] = bucket.filter((entry) => entry.isbn !== isbn); // Filter out the book
    }
  }
}

// Queue Implementation (used for the book waitlist)
class Queue {
  constructor() {
    this.items = []; // Array to hold the queue elements
  }

  // Add a user to the end of the queue
  enqueue(user) {
    this.items.push(user); // Add the user to the end of the queue
  }

  // Remove and return the first user from the queue
  dequeue() {
    return this.items.shift(); // Remove and return the first user
  }

  // Peek at the first user in the queue without removing them
  peek() {
    return this.items[0]; // Return the first user in the queue
  }

  // Check if the queue is empty
  isEmpty() {
    return this.items.length === 0; // Return true if the queue is empty
  }

  // Get the size (number of elements) in the queue
  size() {
    return this.items.length; // Return the length of the queue
  }
}

// Book with Waitlist Implementation
class BookWithWaitlist {
  constructor(title, isbn, author) {
    this.title = title; // The title of the book
    this.isbn = isbn; // The ISBN of the book
    this.author = author; // The author of the book
    this.availability = "Available"; // Availability status of the book
    this.waitlist = new Queue(); // Queue to track users waiting for the book
  }

  // Borrow a book if it's available, otherwise add the user to the waitlist
  borrowBook(user) {
    if (this.availability === "Available") {
      this.availability = "Borrowed"; // Mark the book as borrowed
      console.log(`${user} successfully borrowed ${this.title}.`);
    } else {
      this.waitlist.enqueue(user); // Add the user to the waitlist
      console.log(`${user} has been added to the waitlist for ${this.title}.`);
    }
  }

  // Return the book to the library
  returnBook() {
    if (!this.waitlist.isEmpty()) {
      const nextUser = this.waitlist.dequeue(); // Remove the first user from the waitlist
      console.log(`${nextUser} is now borrowing ${this.title}.`);
    } else {
      this.availability = "Available"; // Mark the book as available
      console.log(`${this.title} is now available.`);
    }
  }

  // Show the current users in the waitlist
  showWaitlist() {
    if (this.waitlist.isEmpty()) {
      console.log(`No users are waiting for ${this.title}.`);
    } else {
      console.log(
        `Waitlist for ${this.title}: ${this.waitlist.items.join(", ")}`
      );
    }
  }
}

// Export all classes for use in other files
export { LinkedList, HashTable, Queue, BookWithWaitlist };
