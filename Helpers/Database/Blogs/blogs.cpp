#include "blogs.h"
#include <memory>
#include <mariadb/conncpp.hpp>
#include "../db_connection.h"
#include "blog_dto.h"

namespace Database
{
    std::vector<Requests::BlogModel> viewBlogs(const std::string& query)
    {
        auto connection = Database::GetConnection();
        
        // The list of blog posts
        std::vector<Requests::BlogModel> posts;

        // Prepare the SELECT statement
        std::unique_ptr<sql::PreparedStatement> statement(
            connection->prepareStatement(
                "SELECT u.username, b.upvotes, b.created_on, b.title, b.content "
                "FROM blogs b "
                "JOIN users u ON b.user_id = u.id "
                "WHERE u.username LIKE ? OR b.title LIKE ?"
            )
        );

        // Prepare the query parameters for LIKE
        
        // In future, we can use a inverted index or alike for faster searches
        std::string likeQuery = "%" + query + "%"; // Wildcards

        statement->setString(1, likeQuery);
        statement->setString(2, likeQuery);

        // Execute the query
        std::unique_ptr<sql::ResultSet> resultSet(statement->executeQuery());

        // Process the results
        while (resultSet->next()) {
            Requests::BlogModel post(
                resultSet->getString("username").c_str(), 
                resultSet->getString("content").c_str(),
                resultSet->getInt("upvotes"),
                resultSet->getString("created_on").c_str(),
                resultSet->getString("title").c_str()
            );

            posts.push_back(post);
        }

        connection->close(); 
        return posts; 
    }

    void createBlog(const Requests::BlogPost& post) {
        auto connection = Database::GetConnection();

        // Prepare the INSERT statement
        std::unique_ptr<sql::PreparedStatement> insertStatement(
            connection->prepareStatement(
                "INSERT INTO blogs (title, content, user_id) VALUES (?, ?, ?)"
            )
        );

        insertStatement->setString(1, post.title);
        insertStatement->setString(2, post.content);
        insertStatement->setInt(3, post.userId);

        insertStatement->executeUpdate(); // Execute the insertion

        connection->close(); 
    }
}