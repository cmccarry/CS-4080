<?php
session_start(); // Start a session to track user login status
require_once 'User.php'; // Include the User class

$userObj = new User();

if ($_SERVER['REQUEST_METHOD'] === 'POST') { // Check if form is submitted (Chapter 8: Control Structures)
    // Authenticate user
    if ($userObj->authenticate($_POST['username'], $_POST['password'])) {
        header("Location: index.php"); // Redirect to home page upon successful login
    } else {
        echo "Invalid username or password."; // Display error message
    }
}
?>

<!-- Login form -->
<form method="POST">
    <label>Username:</label>
    <input type="text" name="username" required>
    <label>Password:</label>
    <input type="password" name="password" required>
    <button type="submit">Login</button>
</form>
