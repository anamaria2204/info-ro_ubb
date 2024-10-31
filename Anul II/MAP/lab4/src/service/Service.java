package service;

import domain.Entity;
import domain.Utilizator;

import java.util.List;
import java.util.Map;
import java.util.Objects;

/**
 * Interface for the service
 * @param <ID> - the type of the if of the entity
 */

public interface Service<ID> {

    /**
     * Adds an user
     * @param firstName - first name
     * @param lastName - last name
     * @param username - user name
     * @return - true id user was added
     *         - throws: Exception is the user is not valid
     */
    boolean addUser(String firstName, String lastName, String username);

    /**
     * Removes an user and if they are friends with someone they get that friendship removed.
     * And also all the friendhips entities that contains this user
     * @param username
     * @return the removed user
     */

    Entity<String> removeUser(String username);

    /**
     * Adds a frienship
     * @param usename1
     * @param usename2
     * @return true if the friendship is created
     *          throw Exception if the users aren't valid
     */

    boolean addFriendship(String usename1, String usename2);

    /**
     * Remove a frienship
     * @param usename1
     * @param usename2
     * @return true if the frienship is removed
     *          throw Exception otherwise
     */

    boolean removeFriendship(String usename1, String usename2);

    /**
     * Shows the number of comunities
     * @return number of comunities
     */

    public Map<String, Object> showNumberofComunities();

    /**
     * List that contains the biggest community
     * @return
     */
    List<Utilizator> biggestCommunity();

    /**
     *
     * @return all users
     */
    Iterable getAllUsers();

    /**
     *
     * @return all friendships
     */
    Iterable getAllFriendships();
}
