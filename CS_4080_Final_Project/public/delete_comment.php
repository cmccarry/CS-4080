<?php
session_start(); // Starts the session to manage user login state
require_once '../classes/Post.php'; // Imports the Post class for managing blog posts and comments

// Check if user is logged in
if (!isset($_SESSION['username'])) {
    header("Location: login.php");
    exit;
}

$commentId = isset($_GET['id']) ? (int)$_GET['id'] : null; // Retrieve comment ID from GET request
$username = $_SESSION['username']; // Get the logged-in username

$postObj = new Post(); // Instantiate Post object for accessing methods

// Get comment by ID to verify ownership
$comment = $postObj->getCommentById($commentId);

if ($comment && $comment['author'] === $username) { // Check if user is the comment's author
    $postObj->deleteComment($commentId); // Delete comment if authorized
    header("Location: index.php"); // Redirect to homepage
    exit;
} else {
    echo "Unauthorized access."; // Output error message
}
?>
