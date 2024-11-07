<?php
// Establishes and returns a database connection
function getDbConnection() {
    // Database connection parameters
    $servername = "localhost";
    $username = "root";
    $password = "";
    $dbname = "cs_4080_project_db";

    // Create a new MySQLi connection
    $conn = new mysqli($servername, $username, $password, $dbname);

    // Check for connection errors and terminate if it fails
    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error); // Basic error handling with die()
    }

    return $conn; // Returns the connection object
}
?>
