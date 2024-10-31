<?php
require_once '../config/config.php';

class User {
    private $db; // Private database connection (Chapter 5: Scope)

    public function __construct() {
        $this->db = getDbConnection(); // DB connection (Chapter 9: Subprogram)
    }

    public function register($username, $password) {
        if ($this->checkUsernameExists($username)) {
            return false;
        }

        $hashedPassword = password_hash($password, PASSWORD_BCRYPT); // Securely hash passwords
        $stmt = $this->db->prepare("INSERT INTO users (username, password) VALUES (?, ?)");
        $stmt->bind_param("ss", $username, $hashedPassword);
        return $stmt->execute();
    }

    public function authenticate($username, $password) {
        $stmt = $this->db->prepare("SELECT password FROM users WHERE username = ?");
        $stmt->bind_param("s", $username);
        $stmt->execute();
        $stmt->bind_result($hashedPassword);
        $stmt->fetch();

        if (password_verify($password, $hashedPassword)) { 
            $_SESSION['username'] = $username; 
            return true;
        }
        return false;
    }

    public function checkUsernameExists($username) {
        $stmt = $this->db->prepare("SELECT id FROM users WHERE username = ?");
        $stmt->bind_param("s", $username);
        $stmt->execute();
        $stmt->store_result();
        return $stmt->num_rows > 0;
    }

    public function verifyPassword($username, $currentPassword) {
        $stmt = $this->db->prepare("SELECT password FROM users WHERE username = ?");
        $stmt->bind_param("s", $username);
        $stmt->execute();
        $stmt->bind_result($hashedPassword);
        $stmt->fetch();
        return password_verify($currentPassword, $hashedPassword);
    }

    public function updatePassword($username, $newPassword) {
        $hashedPassword = password_hash($newPassword, PASSWORD_BCRYPT);
        $stmt = $this->db->prepare("UPDATE users SET password = ? WHERE username = ?");
        $stmt->bind_param("ss", $hashedPassword, $username);
        return $stmt->execute();
    }
}
?>
