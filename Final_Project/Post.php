<?php
require_once 'config.php';

// Post class for handling blog posts (Chapter 11: Data Abstraction, Chapter 12: OOP)
class Post {
    private $db; // Private database connection variable (Chapter 5: Scoping)

    // Constructor to initialize database connection
    public function __construct() {
        $this->db = getDbConnection();
    }

    // Method to create a new post (Chapter 9: Subprograms)
    public function createPost($title, $content, $author) {
        // SQL prepared statement to safely insert new post
        $stmt = $this->db->prepare("INSERT INTO posts (title, content, author) VALUES (?, ?, ?)");
        $stmt->bind_param("sss", $title, $content, $author); // Binding parameters (Chapter 9: Parameter-passing)
        return $stmt->execute(); // Executes the statement
    }

    // Method to retrieve all posts, returning an array (Chapter 6: Associative Arrays)
    public function getAllPosts() {
        $result = $this->db->query("SELECT * FROM posts");
        $posts = []; // Associative array to hold posts data (Chapter 6: Data Types)
        
        // Fetching each row as an associative array and appending to posts
        while ($row = $result->fetch_assoc()) {
            $posts[] = $row; // Populating array with post data
        }
        return $posts; // Returns an array of posts
    }

    // Destructor to close the database connection
    public function __destruct() {
        $this->db->close();
    }
}
?>
