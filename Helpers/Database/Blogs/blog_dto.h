#ifndef BLOG_REQUEST_H
#define BLOG_REQUEST_H

#include "../../../config.h"
#include <string>
#include <utility>

namespace Database::Requests
{
    /**
     * @brief Class representing a blog post model.
     * 
     * This class encapsulates all the details of a blog post, including its ID,
     * username of the author, content, number of upvotes, creation date, title,
     * and user ID.
     */
    class BlogModel
    {
    public:
        /**
         * @brief Constructor for the BlogModel class.
         * 
         * @param id The unique identifier for the blog post.
         * @param username The username of the author.
         * @param content The content of the blog post.
         * @param upvotes The number of upvotes the blog post has received.
         * @param dateCreated The date when the blog post was created.
         * @param title The title of the blog post.
         * @param userId The unique identifier of the user who created the post.
         */
        BlogModel(
            int id,
            std::string username,
            std::string content,
            int upvotes,
            std::string dateCreated,
            std::string title,
            int userId) : id(id),
                          username(std::move(username)),
                          content(std::move(content)),
                          upvotes(upvotes),
                          dateCreated(std::move(dateCreated)),
                          title(std::move(title)),
                          userId(userId) {}

        // Member variables
        int id;                   // Unique identifier for the blog post.
        std::string username;     // Username of the author.
        std::string content;      // Content of the blog post.
        int upvotes;              // Number of upvotes received by the blog post.
        std::string dateCreated;  // Creation date of the blog post.
        std::string title;        // Title of the blog post.
        int userId;              // Unique identifier of the user who created the post.
    };

    /**
     * @brief Class representing a request to create a new blog post.
     * 
     * This class encapsulates the necessary information required to create a new blog
     * post, including its title, content, and associated user ID.
     */
    class BlogPost
    {
    public:
        /**
         * @brief Constructor for the BlogPost class.
         * 
         * @param title The title of the new blog post.
         * @param content The content of the new blog post.
         * @param userId The unique identifier of the user creating the post.
         */
        BlogPost(
            std::string title,
            std::string content,
            int userId) : title(std::move(title)),
                          content(std::move(content)),
                          userId(userId) {}

        std::string title;   // Title of the new blog post.
        std::string content; // Content of the new blog post.
        int userId;         // Unique identifier of the user creating the post.
    };

    /**
     * @brief Class representing a request to update an existing blog post.
     * 
     * This class encapsulates updated information for an existing blog post, including
     * its title, content, and unique identifier (ID).
     */
    class BlogUpdatePost
    {
    public:
        /**
         * @brief Constructor for the BlogUpdatePost class.
         * 
         * @param title The updated title for the blog post.
         * @param content The updated content for the blog post.
         * @param id The unique identifier of the blog post to be updated.
         */
        BlogUpdatePost(
            std::string title,
            std::string content,
            int id) : title(std::move(title)),
                          content(std::move(content)),
                          id(id) {}

        std::string title;   // Updated title for the blog post.
        std::string content; // Updated content for the blog post.
        int id;             // Unique identifier of the blog post to be updated.
    };
}

#endif // BLOG_REQUEST_H