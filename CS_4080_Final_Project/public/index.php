<?php
/* 1 --- Why the '<?php>' tags?
    PHP is a server-side language, meaning that it needs to be able to distinguish code from HTML to know what to process. 
    The <?php tags help the server identify PHP code blocks.
    This allows it to interpret and execute them before sending the final HTML to the user’s browser.
*/

/* What is this file?
    The 'index.php' file serves as the homepage for the blog website.
    It shows all the blog posts and also shows options like creating a new post and adding comments if the user is logged in.
    This and other files have the HTML structure for that page's design and nav menu.
*/

session_start();
/* 1 --- Why the 'session_start()'?
    PHP has built-in session handling that is straightforward, making it easy to implement user authentication.
    'session_start()' is used to store and retrieve $_SESSION variables across the pages to manage login state and user identity.
*/

require_once '../classes/Post.php';

$postObj = new Post();

$authorFilter = isset($_GET['author']) ? $_GET['author'] : '';
$page = isset($_GET['page']) ? (int)$_GET['page'] : 1;
/* 2 --- $GET superglobal
    Used for url query parameters. Here it's being used for author filtering and pagination.
*/
$limit = 5;
$offset = ($page - 1) * $limit;

if ($authorFilter) {
    $posts = $postObj->getPostsByAuthor($authorFilter, $limit, $offset);
} else {
    $posts = $postObj->getAllPosts($limit, $offset);
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Blog Home</title>
    <link rel="stylesheet" href="assets/css/styles.css">
</head>
<body>
    <header class="masthead">
        <a href="index.php"><img src="assets/images/main_img.png" alt="Logo"></a>
        <h1>Blog Website Using PHP!!!</h1>
        <nav class="nav-menu">
            <a href="index.php">Home</a>
            <?php if (isset($_SESSION['username'])): 
                /* 2 --- $_SESSION superglobal
                    Used for session variables. Here it's being used to store the logged-in user's data (username).
                */
                ?>
                <a href="profile.php">Profile</a>
                <a href="new_post.php">Create New Post</a>
                <a href="logout.php">Logout</a>
            <?php else: ?>
                <a href="login.php">Login</a>
            <?php endif; ?>
        </nav>
    </header>

    <div class="container">
        <h2>Blog Posts</h2>
        
        <form method="GET" action="index.php">
            <label>Filter by Author:</label>
            <input type="text" name="author" value="<?= htmlspecialchars($authorFilter); ?>">
            <button type="submit">Filter</button>
        </form>
        
        <hr>

        <?php if (count($posts) > 0): ?>
            <?php foreach ($posts as $post): ?>
                <h3><?= htmlspecialchars($post['title']); ?></h3>
                <p><?= nl2br(htmlspecialchars($post['content'])); ?></p>
                <?php 
                /* 6 --- htmlspecialchars() and nl2br()
                    htmlspecialchars() function converts special characters (&, ", ', <, >)to HTML entities.
                    nl2br() function converts newline characters to <br> tags in HTML and preserves line breaks for the output.
                */

                /* 7 --- Shorthand echo tags ( <?= ... ?> )
                    <?= ... ?> is shorthand for <?php echo ... ?>.
                    Used to output values directly within HTML, allows for quick inline input.
                */
                ?>
                <small>by <?= htmlspecialchars($post['author']); ?> on <?= htmlspecialchars($post['created_at']); ?></small>
                <?php if (isset($_SESSION['username']) && $_SESSION['username'] === $post['author']): ?>
                    <a href="edit_post.php?id=<?= $post['id']; ?>">Edit</a> |
                    <a href="delete_post.php?id=<?= $post['id']; ?>" onclick="return confirm('Are you sure you want to delete this post?');">Delete</a>
                <?php endif; ?>
                <h4>Comments:</h4>
                <?php
                $comments = $postObj->getCommentsByPostId($post['id']);
                foreach ($comments as $comment): ?>
                    <p><strong><?= htmlspecialchars($comment['author']); ?></strong>: <?= nl2br(htmlspecialchars($comment['content'])); ?>
                    <?php if (isset($_SESSION['username']) && $_SESSION['username'] === $comment['author']): ?>
                        <a href="delete_comment.php?id=<?= $comment['id']; ?>" onclick="return confirm('Are you sure you want to delete this comment?');">Delete</a>
                    <?php endif; ?>
                    </p>
                <?php endforeach; ?>
                <?php if (isset($_SESSION['username'])): ?>
                    <form method="POST" action="add_comment.php">
                        <input type="hidden" name="post_id" value="<?= $post['id']; ?>">
                        <textarea name="content" required placeholder="Add a comment"></textarea>
                        <button type="submit">Submit</button>
                    </form>
                <?php endif; ?>
                <hr>
            <?php endforeach; ?>
        <?php else: ?>
            <p>No posts available.</p>
        <?php endif; ?>

        <div class="pagination">
            <?php if ($page > 1): ?>
                <a href="?page=<?= $page - 1; ?>&author=<?= urlencode($authorFilter); ?>">Previous</a>
            <?php endif; ?>
            <a href="?page=<?= $page + 1; ?>&author=<?= urlencode($authorFilter); ?>">Next</a>
        </div>
    </div>
</body>
</html>
