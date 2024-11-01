<?php
// Establishes and returns a database connection
function getDbConnection() {
    // Database connection parameters
    $servername = "localhost";
    $username = "root";
    $password = ""; // Chapter 7: Assignment statement to store credentials
    $dbname = "cs_4080_project_db";

    // Create a new MySQLi connection
    $conn = new mysqli($servername, $username, $password, $dbname); // (Chapter 6: Data Types, mysqli as object data type)

    // Check for connection errors and terminate if it fails
    if ($conn->connect_error) { // Chapter 8: Control Structure - if condition
        die("Connection failed: " . $conn->connect_error); // Chapter 14: Basic error handling with die()
    }

    return $conn; // Returns the connection object (Chapter 9: Subprogram for reusable connection)
}
?>
