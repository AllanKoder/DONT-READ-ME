#include "blogs.h"
#include <memory>
#include <mariadb/conncpp.hpp>
#include "../db_connection.h"

namespace Database
{
    std::vector<Requests::BlogPost> viewBlogs(const std::string& query)
    {
        auto connection = Database::GetConnection();
        
        // The list of blog posts
        std::vector<Requests::BlogPost> posts;

        // Prepare the SELECT statement
        std::unique_ptr<sql::PreparedStatement> statement(
            connection->prepareStatement(
                "SELECT u.username, b.upvotes, b.created_on, b.title "
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
            Requests::BlogPost post;
            post.username = resultSet->getString("username");
            post.upvotes = resultSet->getInt("upvotes");
            post.dateCreated = resultSet->getString("created_on");
            post.title = resultSet->getString("title");
            posts.push_back(post);
        }

        connection->close(); 
        return posts; 
    }
}