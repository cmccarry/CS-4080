<?php
session_start(); // Start session to track user login status
require_once 'Post.php'; // Include the Post class

// Check if user is logged in (Chapter 8: Control Structures, conditionals)
if (!isset($_SESSION['username'])) {
    header("Location: login.php"); // Redirect to login if not authenticated
    exit;
}

$postObj = new Post(); // Instantiate Post class for creating new posts

if ($_SERVER['REQUEST_METHOD'] === 'POST') { // Check if form is submitted
    // Call createPost with form inputs (Chapter 9: Subprograms)
    $postObj->createPost($_POST['title'], $_POST['content'], $_SESSION['username']);
    header("Location: index.php"); // Redirect to home page after post creation
}
?>

<!-- Form to create a new blog post -->
<form method="POST">
    <label>Title:</label>
    <input type="text" name="title" required>
    <label>Content:</label>
    <textarea name="content" required></textarea>
    <button type="submit">Create Post</button>
</form>
