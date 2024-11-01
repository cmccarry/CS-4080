<?php
session_start();
require_once '../classes/Post.php';

// Check if user is logged in
if (!isset($_SESSION['username'])) {
    header("Location: login.php");
    exit;
}

$postObj = new Post(); // Instantiate Post object

$postId = isset($_GET['id']) ? (int)$_GET['id'] : null; // Get post ID from request
$post = $postObj->getPostById($postId); // Retrieve post details

if (!$post || $post['author'] !== $_SESSION['username']) { // Check if post exists and user is the author
    echo "Unauthorized access.";
    exit;
}

if ($_SERVER['REQUEST_METHOD'] === 'POST') { // Process form submission
    $title = $_POST['title'];
    $content = $_POST['content'];
    $postObj->updatePost($postId, $title, $content); // Update post content
    header("Location: index.php"); // Redirect to homepage
    exit;
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Edit Post</title>
    <link rel="stylesheet" href="assets/css/styles.css">
</head>
<body>
    <header class="masthead">
        <a href="index.php"><img src="assets/images/main_img.png" alt="Logo"></a>
        <h1>Edit Post</h1>
        <a href="index.php">Home</a>
    </header>

    <div class="container">
        <h2>Edit Post</h2>
        <form method="POST">
            <label>Title:</label>
            <input type="text" name="title" value="<?= htmlspecialchars($post['title']); ?>" required>
            
            <label>Content:</label>
            <textarea name="content" required rows="10" cols="30"><?= htmlspecialchars($post['content']); ?></textarea>
            
            <button type="submit">Update Post</button>
        </form>
    </div>
</body>
</html>
