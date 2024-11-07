<?php
session_start(); // Starts the session to manage user login state
require_once '../classes/Post.php'; // Imports the Post class for managing blog posts and comments

// Check if user is logged in
if (!isset($_SESSION['username'])) {
    header("Location: login.php");
    exit;
}

// Retrieve the post ID and comment content from the form submission
$postId = $_POST['post_id'];
$content = $_POST['content'];
/* 2 --- $_POST superglobal
    Used to handle form submission data. Here it's being used to grab data from a submitted form to add a comment to a post.
*/
$author = $_SESSION['username'];

// Instantiate Post object and add comment to database
$postObj = new Post();
$postObj->addComment($postId, $author, $content);

// Redirect back to the main page after the comment is added
header("Location: index.php");
exit;
?>
