#ifndef DATABASE_BLOGS_H
#define DATABASE_BLOGS_H

#include <memory>
#include <mariadb/conncpp.hpp>
#include "blog_dto.h"
#include <vector>
#include <optional>

namespace Database
{
    /**
     * @brief Retrieves a list of blog posts based on a query.
     * 
     * This function executes the provided query and returns a vector of BlogModel objects 
     * representing the blogs that match the query criteria.
     * 
     * @param query The query (name or creator) for fetching.
     * @return std::vector<Requests::BlogModel> A vector containing the retrieved blog posts.
     */
    std::vector<Requests::BlogModel> viewBlogs(const std::string &query);

    /**
     * @brief Retrieves a specific blog post by its ID.
     * 
     * This function fetches a single blog post from the database based on its unique identifier.
     * 
     * @param id The unique identifier of the blog post to retrieve.
     * @return std::optional<Requests::BlogModel> An optional containing the BlogModel if found, otherwise nullopt.
     */
    std::optional<Requests::BlogModel> viewBlog(int id);

    /**
     * @brief Increments the upvote count for a specific blog post.
     * 
     * This function increases the upvote count for the blog identified by the given ID.
     * 
     * @param id The unique identifier of the blog post to upvote.
     */
    void upvoteBlog(int id);

    /**
     * @brief Decrements the downvote count for a specific blog post.
     * 
     * This function decreases the downvote count for the blog identified by the given ID.
     * 
     * @param id The unique identifier of the blog post to downvote.
     */
    void downvoteBlog(int id);

    /**
     * @brief Creates a new blog post in the database.
     * 
     * This function takes a BlogPost object containing the details of the new blog and inserts it into the database.
     * 
     * @param post A constant reference to a BlogPost object containing the details of the blog to be created.
     */
    void createBlog(const Requests::BlogPost &post);

    /**
     * @brief Updates an existing blog post in the database.
     * 
     * This function takes a BlogUpdatePost object containing updated information for an existing blog
     * and applies those changes in the database.
     * 
     * @param post A constant reference to a BlogUpdatePost object containing updated details of the blog.
     */
    void updateBlog(const Requests::BlogUpdatePost &post);
}

#endif 