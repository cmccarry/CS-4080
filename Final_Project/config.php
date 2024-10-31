<?php
// Defining constants for database connection settings (Chapter 5: Names and Bindings)
// Constants ensure that these values remain the same throughout the application
define('DB_HOST', 'localhost');
define('DB_USER', 'root');
define('DB_PASS', '');
define('DB_NAME', 'CS_4080_Project_DB');

// Function to establish and return a database connection
function getDbConnection() {
    // Creating a new MySQLi connection (Data type: Object, Chapter 6)
    $conn = new mysqli(DB_HOST, DB_USER, DB_PASS, DB_NAME);

    // Exception handling if the connection fails (Chapter 14: Exception Handling)
    if ($conn->connect_error) {
        throw new Exception('Database connection error: ' . $conn->connect_error);
    }
    return $conn; // Returns the database connection object
}
?>
