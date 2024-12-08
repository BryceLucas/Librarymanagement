// Wait for the DOM content to load before running any script
document.addEventListener("DOMContentLoaded", () => {
  const bookListElement = document.getElementById("book-list"); // Reference to the element where book list items will be displayed
  const searchBox = document.getElementById("search-box"); // Reference to the search box for filtering books

  let books = []; // Array to store the list of books fetched from books.json

  // Fetch books from the JSON file and populate the book list
  fetch("booklist/books.json")
    .then((response) => {
      if (!response.ok) {
        throw new Error("Failed to fetch books.json"); // Handle unsuccessful response
      }
      return response.json(); // Parse the JSON response
    })
    .then((data) => {
      books = data; // Store the book data in the 'books' array
      displayBooks(books, bookListElement); // Display all books in the book list
    })
    .catch((error) => {
      console.error("Error loading books:", error); // Log any errors that occur during the fetch process
      bookListElement.innerHTML = `<p>Error loading book list. Please try again later.</p>`; // Display an error message
    });

  // Add event listener to handle real-time search input
  searchBox.addEventListener("input", (event) => {
    const query = event.target.value.toLowerCase(); // Get the search query and convert it to lowercase
    const filteredBooks = books.filter(
      (book) =>
        book.title.toLowerCase().includes(query) || // Filter by book title
        book.author.toLowerCase().includes(query) || // Filter by author name
        book.isbn.toLowerCase().includes(query) // Filter by ISBN
    );
    displayBooks(filteredBooks, bookListElement); // Display only the filtered books
  });

  // Event delegation for borrow and return buttons
  bookListElement.addEventListener("click", (event) => {
    const target = event.target;

    if (target.classList.contains("borrow-btn")) {
      // Borrow button clicked
      const { bookId } = target.dataset; // Extract bookId from the button's data attributes
      const userName = prompt("Enter your name to borrow this book:"); // Prompt user for their name
      if (userName) {
        borrowBook(bookId, userName); // Call the borrowBook function to handle the borrowing logic
        displayBooks(books, bookListElement); // Refresh the book list to reflect the updated status
      }
    }

    if (target.classList.contains("return-btn")) {
      // Return button clicked
      const { bookId } = target.dataset; // Extract bookId from the button's data attributes
      returnBook(bookId); // Call the returnBook function to handle the return logic
      displayBooks(books, bookListElement); // Refresh the book list to reflect the updated status
    }
  });

  /**
   * Borrow a book from the library
   * @param {number} bookId - The ID of the book to borrow
   * @param {string} userName - The name of the user borrowing the book
   */
  function borrowBook(bookId, userName) {
    const book = books.find((b) => b.id == bookId); // Find the book in the list by its ID
    if (book.availability === "Available") {
      // If the book is available, change its status to "Borrowed"
      book.availability = "Borrowed";
      alert(`${userName} successfully borrowed ${book.title}.`);
    } else if (!book.waiting_list.includes(userName)) {
      // If the book is not available, add the user to the waitlist if they are not already on it
      book.waiting_list.push(userName);
      alert(`${userName} has been added to the waitlist for ${book.title}.`);
    } else {
      // If the user is already on the waitlist, display a message
      alert(`${userName} is already in the waitlist for ${book.title}.`);
    }
  }

  /**
   * Return a book to the library
   * @param {number} bookId - The ID of the book to return
   */
  function returnBook(bookId) {
    const book = books.find((b) => b.id == bookId); // Find the book in the list by its ID
    if (book.waiting_list.length > 0) {
      // If there are users on the waitlist, the first user in line gets the book
      const nextUser = book.waiting_list.shift(); // Remove the first user from the waitlist
      alert(`${nextUser} is now borrowing ${book.title}.`);
    } else {
      // If there is no waitlist, mark the book as available
      book.availability = "Available";
      alert(`${book.title} is now available.`);
    }
  }

  /**
   * Display a list of books in the container
   * @param {Array} books - The list of books to display
   * @param {HTMLElement} container - The container element where the book list will be rendered
   */
  function displayBooks(books, container) {
    container.innerHTML = ""; // Clear any existing content in the container

    books.forEach((book) => {
      const listItem = document.createElement("li"); // Create a list item for the book
      listItem.className = `book-item ${
        book.availability.toLowerCase() === "available"
          ? "book-available" // Apply "book-available" class if the book is available
          : "book-checked-out" // Apply "book-checked-out" class if the book is borrowed
      }`;

      // Book HTML structure for each list item
      listItem.innerHTML = `
        <img src="${book.image}" alt="${book.title}" class="book-cover">
        <div class="book-details">
            <h3>${book.title}</h3>
            <p><strong>Author:</strong> ${book.author}</p>
            <p><strong>ISBN:</strong> ${book.isbn}</p>
            <p><strong>Availability:</strong> ${book.availability}</p>
            <p><strong>Waitlist:</strong> ${
              book.waiting_list.length > 0
                ? book.waiting_list.join(", ") // List all users in the waitlist
                : "None" // If there is no waitlist, display "None"
            }</p>
            <button class="borrow-btn" data-book-id="${book.id}">Borrow</button>
            <button class="return-btn" data-book-id="${book.id}">Return</button>
        </div>
      `;

      // Append the list item to the container
      container.appendChild(listItem);
    });
  }
});
