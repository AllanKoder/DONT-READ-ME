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
            connection->prepareStatement("SELECT u.username, b.created_on, b.title FROM blogs b JOIN users u ON b.user_id = u.id")
        );

        // Execute the query
        std::unique_ptr<sql::ResultSet> resultSet(statement->executeQuery());

        // Process the results
        while (resultSet->next()) {
            Requests::BlogPost post;
            post.name = resultSet->getString("username");
            post.dateCreated = resultSet->getString("created_on");
            post.title = resultSet->getString("title");
            posts.push_back(post);
        }

        connection->close(); 
        return posts; 
    }
}