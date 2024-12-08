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
});

// Function to display books in the #book-list section
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
            </div>
        `;

    // Append to the container
    container.appendChild(listItem);
});
}
