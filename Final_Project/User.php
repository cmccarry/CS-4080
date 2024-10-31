<?php
require_once 'config.php';

// Class User to encapsulate all user-related operations (Chapter 11: Encapsulation, Chapter 12: OOP)
class User {
    private $db; // Private variable for database connection (Chapter 5: Scoping)

    // Constructor to initialize the database connection (Object-oriented feature)
    public function __construct() {
        $this->db = getDbConnection(); // Using function from config.php
    }

    // Method to register a new user (Chapter 9: Subprograms, functions to encapsulate behavior)
    public function register($username, $password) {
        // Using password_hash function to securely hash passwords (built-in function, Chapter 7: Expressions)
        $hashedPassword = password_hash($password, PASSWORD_BCRYPT);

        // Preparing SQL statement for secure insertion (binding parameters, Chapter 9: Parameter-passing)
        $stmt = $this->db->prepare("INSERT INTO users (username, password) VALUES (?, ?)");
        $stmt->bind_param("ss", $username, $hashedPassword);

        // Execute the statement and return the success status
        return $stmt->execute();
    }

    // Method to authenticate a user (Chapter 9: Functions/Subprograms, process abstraction)
    public function authenticate($username, $password) {
        // Prepared statement to retrieve hashed password for the given username
        $stmt = $this->db->prepare("SELECT password FROM users WHERE username = ?");
        $stmt->bind_param("s", $username);
        $stmt->execute();
        
        // Binding the result to retrieve the hashed password
        $stmt->bind_result($hashedPassword);
        $stmt->fetch();

        // Verifying the input password against the stored hashed password
        if (password_verify($password, $hashedPassword)) {
            $_SESSION['username'] = $username; // Setting session variable for authenticated user
            return true;
        }
        return false; // Authentication failed
    }

    // Destructor to close the database connection (Resource management, Chapter 10: Subprograms)
    public function __destruct() {
        $this->db->close(); // Closing connection to prevent resource leaks
    }
}
?>
