<?php
require_once '../config/config.php';

// Post class to manage posts and comments (Chapter 11: Encapsulation, Chapter 12: OOP)
class Post {
    private $db; // Private database connection property (Chapter 5: Scope, Chapter 6: Data Types)

    // Constructor: establishes database connection (Chapter 9: Subprograms, reusable DB access)
    public function __construct() {
        $this->db = getDbConnection();
    }

    /* ====== Post Management Functions ====== */

    // Retrieves all posts, with pagination (limit and offset for the current page)
    public function getAllPosts($limit, $offset) {
        $stmt = $this->db->prepare("SELECT * FROM posts ORDER BY created_at DESC LIMIT ? OFFSET ?");
        $stmt->bind_param("ii", $limit, $offset); // Chapter 9: Parameter passing
        $stmt->execute();
        return $stmt->get_result()->fetch_all(MYSQLI_ASSOC);
    }

    // Retrieves posts authored by a specific user, with pagination
    public function getPostsByAuthor($author, $limit, $offset) {
        $stmt = $this->db->prepare("SELECT * FROM posts WHERE author = ? ORDER BY created_at DESC LIMIT ? OFFSET ?");
        $stmt->bind_param("sii", $author, $limit, $offset);
        $stmt->execute();
        return $stmt->get_result()->fetch_all(MYSQLI_ASSOC);
    }

    // Retrieves all posts authored by a specific user
    public function getPostsByUser($username) {
        $stmt = $this->db->prepare("SELECT * FROM posts WHERE author = ? ORDER BY created_at DESC");
        $stmt->bind_param("s", $username);
        $stmt->execute();
        return $stmt->get_result()->fetch_all(MYSQLI_ASSOC);
    }
    
    // Creates a new post
    public function createPost($title, $content, $author) {
        $stmt = $this->db->prepare("INSERT INTO posts (title, content, author) VALUES (?, ?, ?)");
        $stmt->bind_param("sss", $title, $content, $author);
        return $stmt->execute(); // Returns true on success, false otherwise
    }

    // Retrieves a specific post by its unique ID
    public function getPostById($postId) {
        $stmt = $this->db->prepare("SELECT * FROM posts WHERE id = ?");
        $stmt->bind_param("i", $postId);
        $stmt->execute();
        return $stmt->get_result()->fetch_assoc(); // Returns post details or null if not found
    }

    // Updates the title and content of an existing post
    public function updatePost($postId, $title, $content) {
        $stmt = $this->db->prepare("UPDATE posts SET title = ?, content = ? WHERE id = ?");
        $stmt->bind_param("ssi", $title, $content, $postId);
        return $stmt->execute();
    }

    // Deletes a post by its unique ID
    public function deletePost($postId) {
        $stmt = $this->db->prepare("DELETE FROM posts WHERE id = ?");
        $stmt->bind_param("i", $postId);
        return $stmt->execute();
    }

    /* ====== Comment Management Functions ====== */

    // Retrieves comments for a specific post, ordered by creation time
    public function getCommentsByPostId($postId) {
        $stmt = $this->db->prepare("SELECT * FROM comments WHERE post_id = ? ORDER BY created_at ASC");
        $stmt->bind_param("i", $postId);
        $stmt->execute();
        return $stmt->get_result()->fetch_all(MYSQLI_ASSOC);
    }

    // Adds a new comment to a specified post
    public function addComment($postId, $author, $content) {
        $stmt = $this->db->prepare("INSERT INTO comments (post_id, author, content) VALUES (?, ?, ?)");
        $stmt->bind_param("iss", $postId, $author, $content);
        return $stmt->execute();
    }

    // Retrieves a specific comment by its unique ID
    public function getCommentById($commentId) {
        $stmt = $this->db->prepare("SELECT * FROM comments WHERE id = ?");
        $stmt->bind_param("i", $commentId);
        $stmt->execute();
        return $stmt->get_result()->fetch_assoc();
    }

    // Deletes a comment by its unique ID
    public function deleteComment($commentId) {
        $stmt = $this->db->prepare("DELETE FROM comments WHERE id = ?");
        $stmt->bind_param("i", $commentId);
        return $stmt->execute();
    }

    /* ====== User Account Management Functions ====== */

    // Retrieves user information by username
    public function getUserInfo($username) {
        $stmt = $this->db->prepare("SELECT username, created_at FROM users WHERE username = ?");
        $stmt->bind_param("s", $username);
        $stmt->execute();
        return $stmt->get_result()->fetch_assoc();
    }

    // Updates the username for a specific user
    public function updateUsername($currentUsername, $newUsername) {
        $stmt = $this->db->prepare("UPDATE users SET username = ? WHERE username = ?");
        $stmt->bind_param("ss", $newUsername, $currentUsername);
        return $stmt->execute();
    }

    // Checks if a username already exists
    public function checkUsernameExists($username) {
        $stmt = $this->db->prepare("SELECT id FROM users WHERE username = ?");
        $stmt->bind_param("s", $username);
        $stmt->execute();
        $stmt->store_result();
        return $stmt->num_rows > 0;
    }

    // Verifies if the given current password matches the stored password for a user
    public function verifyPassword($username, $currentPassword) {
        $stmt = $this->db->prepare("SELECT password FROM users WHERE username = ?");
        $stmt->bind_param("s", $username);
        $stmt->execute();
        $stmt->bind_result($hashedPassword);
        $stmt->fetch();
        return password_verify($currentPassword, $hashedPassword);
    }

    // Updates the password for a specific user
    public function updatePassword($username, $newPassword) {
        $hashedPassword = password_hash($newPassword, PASSWORD_BCRYPT); // Password hashing for security (Chapter 7: Expressions, Chapter 12: OOP - data protection)
        $stmt = $this->db->prepare("UPDATE users SET password = ? WHERE username = ?");
        $stmt->bind_param("ss", $hashedPassword, $username);
        return $stmt->execute();
    }

    // Destructor: closes the database connection (Chapter 9: Subprograms for resource management)
    public function __destruct() {
        $this->db->close();
    }
}
?>
