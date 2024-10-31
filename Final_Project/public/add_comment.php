<?php
session_start(); // Starts the session to manage user login state
require_once '../classes/Post.php'; // Imports the Post class for managing blog posts and comments (Chapter 11: Encapsulation, using ADT to manage data access)

// Check if the user is logged in
if (!isset($_SESSION['username'])) { // Chapter 8: Control Structure - conditional statement
    header("Location: login.php");
    exit;
}

// Retrieve the post ID and comment content from the form submission
$postId = $_POST['post_id'];
$content = $_POST['content'];
$author = $_SESSION['username']; // Uses session variable to identify the author (Chapter 5: Scope, persistent session data)

// Instantiate Post object and add comment to database
$postObj = new Post(); // Object-Oriented Programming (Chapter 12: OOP, encapsulation of Post operations)
$postObj->addComment($postId, $author, $content); // Encapsulation of add comment functionality (Chapter 9: Subprogram for structured data access)

// Redirect back to the main page after the comment is added
header("Location: index.php");
exit;
?>
