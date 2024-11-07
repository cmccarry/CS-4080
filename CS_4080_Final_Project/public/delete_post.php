<?php
session_start();
require_once '../classes/Post.php';

// Check if user is logged in
if (!isset($_SESSION['username'])) {
    header("Location: login.php");
    exit;
}

$postId = isset($_GET['id']) ? (int)$_GET['id'] : null; // Get post ID from GET request
$username = $_SESSION['username'];

$postObj = new Post(); // Instantiate Post object

$post = $postObj->getPostById($postId); // Get the post by ID to verify ownership

if ($post && $post['author'] === $username) {
    $postObj->deletePost($postId); // Delete post if user is the author
    header("Location: index.php"); // Redirect back to homepage
    exit;
} else {
    echo "Unauthorized access."; // Display if error
}
?>
