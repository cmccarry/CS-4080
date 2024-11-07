<?php
session_start();
require_once '../classes/Post.php';

// Check if user is logged in
if (!isset($_SESSION['username'])) {
    header("Location: login.php");
    exit;
}

$postObj = new Post();

if ($_SERVER['REQUEST_METHOD'] === 'POST') { // Handles form submission
    $title = $_POST['title'];
    $content = $_POST['content'];
    $author = $_SESSION['username'];
    
    $postObj->createPost($title, $content, $author); // Save new post using encapsulated method
    header("Location: index.php"); // Redirect to homepage after posting
    exit;
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Create New Post</title>
    <link rel="stylesheet" href="assets/css/styles.css">
</head>
<body>
    <header class="masthead">
        <a href="index.php"><img src="assets/images/main_img.png" alt="Logo"></a>
        <h1>Create a New Post</h1>
        <nav class="nav-menu">
            <a href="index.php">Home</a>
            <a href="profile.php">Profile</a>
            <a href="new_post.php">Create New Post</a>
            <a href="logout.php">Logout</a>
        </nav>
    </header>

    <div class="container">
        <h2>Create New Post</h2>
        <form method="POST">
            <label>Title:</label>
            <input type="text" name="title" required>
            
            <label>Content:</label>
            <textarea name="content" required rows="10" cols="30"></textarea>
            
            <button type="submit">Post</button>
        </form>
    </div>
</body>
</html>
