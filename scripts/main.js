document.addEventListener("DOMContentLoaded", () => {
  const bookListElement = document.getElementById("book-list");
  const searchBox = document.getElementById("search-box");

  let books = [];

  // Fetch books from books.json
  fetch("booklist/books.json")
    .then((response) => {
      if (!response.ok) {
        throw new Error("Failed to fetch books.json");
      }
      return response.json();
    })
    .then((data) => {
      books = data; // Store books for search functionality
      displayBooks(books, bookListElement);
    })
    .catch((error) => {
      console.error("Error loading books:", error);
      bookListElement.innerHTML = `<p>Error loading book list. Please try again later.</p>`;
    });

  // Search functionality
  searchBox.addEventListener("input", (event) => {
    const query = event.target.value.toLowerCase();
    const filteredBooks = books.filter(
      (book) =>
        book.title.toLowerCase().includes(query) ||
        book.author.toLowerCase().includes(query) ||
        book.isbn.toLowerCase().includes(query)
    );
    displayBooks(filteredBooks, bookListElement);
  });

  // Add event listeners for borrow and return buttons
  bookListElement.addEventListener("click", (event) => {
    const target = event.target;

    if (target.classList.contains("borrow-btn")) {
      const bookId = target.dataset.bookId;
      const userName = prompt("Enter your name to borrow this book:");
      if (userName) {
        borrowBook(bookId, userName);
        displayBooks(books, bookListElement);
      }
    }

    if (target.classList.contains("return-btn")) {
      const bookId = target.dataset.bookId;
      returnBook(bookId);
      displayBooks(books, bookListElement);
    }
  });

  // Borrow book function
  function borrowBook(bookId, userName) {
    const book = books.find((b) => b.id == bookId);
    if (book.availability === "Available") {
      book.availability = "Borrowed";
      alert(`${userName} successfully borrowed ${book.title}.`);
    } else {
      if (!book.waiting_list.includes(userName)) {
        book.waiting_list.push(userName);
        alert(`${userName} has been added to the waitlist for ${book.title}.`);
      } else {
        alert(`${userName} is already in the waitlist for ${book.title}.`);
      }
    }
  }

  // Return book function
  function returnBook(bookId) {
    const book = books.find((b) => b.id == bookId);
    if (book.waiting_list.length > 0) {
      const nextUser = book.waiting_list.shift(); // Remove the first user in the waitlist
      alert(`${nextUser} is now borrowing ${book.title}.`);
    } else {
      book.availability = "Available";
      alert(`${book.title} is now available.`);
    }
  }

  // Function to display books
  function displayBooks(books, container) {
    container.innerHTML = ""; // Clear any existing content

    books.forEach((book) => {
      const listItem = document.createElement("li");
      listItem.className = `book-item ${
        book.availability.toLowerCase() === "available"
          ? "book-available"
          : "book-checked-out"
      }`;

      // Book HTML structure
      listItem.innerHTML = `
                <img src="${book.image}" alt="${book.title}" class="book-cover">
                <div class="book-details">
                    <h3>${book.title}</h3>
                    <p><strong>Author:</strong> ${book.author}</p>
                    <p><strong>ISBN:</strong> ${book.isbn}</p>
                    <p><strong>Availability:</strong> ${book.availability}</p>
                    <p><strong>Waitlist:</strong> ${
                      book.waiting_list.length > 0
                        ? book.waiting_list.join(", ")
                        : "None"
                    }</p>
                    <button class="borrow-btn" data-book-id="${
                      book.id
                    }">Borrow</button>
                    <button class="return-btn" data-book-id="${
                      book.id
                    }">Return</button>
                </div>
            `;

      // Append to the container
      container.appendChild(listItem);
    });
  }
});
