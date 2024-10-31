package service;

import domain.Entity;
import domain.Friendship;
import domain.Tuple;
import domain.Utilizator;
import exceptions.ServiceException;
import repository.Repository;

import java.rmi.ServerException;
import java.time.LocalDateTime;
import java.util.*;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.stream.StreamSupport;

public class Service_Net implements Service<Integer>{

    private final Repository userRepo;
    private final Repository frienshipRepo;
    public Set<Utilizator> set;

    /**
     * Constructor for service
     * @param userRepo - repository
     * @param frienshipRepo - repository for friendships
     */

    public Service_Net(Repository userRepo, Repository frienshipRepo) {
        this.userRepo = userRepo;
        this.frienshipRepo = frienshipRepo;
    }

    /**
     * Adds an user
     * @param firstName - first name
     * @param lastName - last name
     * @param username - user name
     * @return true if the user was added
     */
    @Override
    public boolean addUser(String firstName, String lastName, String username) {
        Utilizator u = new Utilizator(firstName, lastName, username);
        userRepo.save(u);
        return true;
    }

    /**
     * Remove method
     * @param username
     * @return user to be deleted
     */

    @Override
    public Entity<String> removeUser(String username) {
        Utilizator u = findOne(username);
        if(u == null){
            throw new ServiceException("User-ul nu a fost gasit!");
        }
        List<Utilizator> friends = new ArrayList<>(u.getFriendship());
        try {
            friends.forEach(friend -> removeFriendship(u.getUsername(), friend.getUsername()));
        }
        catch (ServiceException e) {

        }
        u.getFriendship().clear();

        Optional<Entity<String>> deletedUser = userRepo.delete(u.getId());
        return deletedUser.get();
    }

    /**
     * Adds a frienship
     * @param usename1
     * @param usename2
     * @return
     */

    @Override
    public boolean addFriendship(String usename1, String usename2) {
        Utilizator user1 = findOne(usename1);
        Utilizator user2 = findOne(usename2);
        Friendship friendship = new Friendship(user1, user2, LocalDateTime.now());

        frienshipRepo.save(friendship);
        addFriendToUsers(user1, user2);
        return true;
    }

    /**
     * Removes a friendship
     * @param usename1 - first user in the friendship
     * @param usename2 - second user in the friendship
     * @return true if the friendship was deleted succesfuly
     */
    @Override
    public boolean removeFriendship(String usename1, String usename2) {
        Utilizator user1 = findOne(usename1);
        Utilizator user2 = findOne(usename2);
        Friendship friendship = findFriendship(user1, user2);
        if(friendship == null){
            throw new ServiceException("Nu a fost gasita prietenia");
        }

        ArrayList<Utilizator> friendshipListUser1 = user1.getFriendship();
        ArrayList<Utilizator> friendshipListUser2 = user2.getFriendship();
        friendshipListUser1.remove(user2);
        friendshipListUser2.remove(user1);

        user1.setFriendship(friendshipListUser1);
        user2.setFriendship(friendshipListUser2);

        userRepo.update(user1);
        userRepo.update(user2);

        frienshipRepo.delete(friendship.getId());
        return true;
    }

    /**
     * Method that shows all the comunities
     * @return the number of comunities
     */

   @Override
    public Map<String, Object> showNumberofComunities() {
        Iterable<Utilizator> utilizatori = userRepo.findAll();
        set = new HashSet<>();
        List<List<Utilizator>> comunitati = new ArrayList<>();

        AtomicInteger numar = new AtomicInteger(0);

        StreamSupport.stream(utilizatori.spliterator(), false)
            .filter(u -> !set.contains(u))
            .map(u -> {
                List<Utilizator> comunitate = DFS(u);
                numar.incrementAndGet();
                return comunitate;
            })
            .forEach(comunitati::add);

        Map<String, Object> rezultat = new HashMap<>();
        rezultat.put("Numarul de comunitati", numar);
        rezultat.put("Comunitati", comunitati);
        return rezultat;
    }

    @Override
    public List<Utilizator> biggestCommunity() {
        Map<String, Object> rezultat = showNumberofComunities();
        List<List<Utilizator>> comunitate = (List<List<Utilizator>>) rezultat.get("Comunitati");

        List<Utilizator> biggestComunitate = new ArrayList<>();

        return comunitate.stream()
                .max(Comparator.comparingInt(List::size))
                .orElse(new ArrayList<>());
    }

    @Override
    public Iterable getAllUsers() {
        return userRepo.findAll();
    }

    @Override
    public Iterable getAllFriendships() {
        return frienshipRepo.findAll();
    }

    private Utilizator findOne(String username) {
        return (Utilizator) StreamSupport.stream(userRepo.findAll().spliterator(),false)
                .filter(user->((Utilizator)user).getUsername().equals(username))
                .findFirst()
                .orElse(null);
    }

    private void addFriendToUsers(Utilizator u1, Utilizator u2){
        ArrayList<Utilizator> newfriendsUser1 = new ArrayList<>(u1.getFriendship());
        ArrayList<Utilizator> newfriendsUser2 = new ArrayList<>(u2.getFriendship());
        if(newfriendsUser1.contains(u2)){
            throw new ServiceException("Cei doi utilizatori sunt prieteni");
        }
        newfriendsUser1.add(u2);

        if(u2.getFriendship().contains(u2)){
            throw new ServiceException("Cei doi utilizatori sunt prieteni");
        }

        newfriendsUser2.add(u1);

        u1.setFriendship(newfriendsUser1);
        u2.setFriendship(newfriendsUser2);

        userRepo.update(u1);
        userRepo.update(u2);

    }

    private Friendship findFriendship(Utilizator user1, Utilizator user2){
        Tuple<Integer, Integer> id = new Tuple<>(user1.getId(), user2.getId());
        Optional<Friendship> friendship = frienshipRepo.findOne(id);
        if(friendship.isEmpty()){
            Tuple<Integer, Integer> id2 = new Tuple<>(user2.getId(), user1.getId());
            friendship = frienshipRepo.findOne(id2);
        }
        return friendship.get();
    }

    private ArrayList<Utilizator> DFS(Utilizator u){
        ArrayList<Utilizator> comunitate = new ArrayList<>();
        ArrayList<Utilizator> deVizitat = new ArrayList<>();

        deVizitat.add(u);
        set.add(u);

        while (!deVizitat.isEmpty()) {
            Utilizator curent = deVizitat.remove(deVizitat.size() - 1);
            comunitate.add(curent);

            for (Utilizator prieten : curent.getFriendship()) {
                if (!set.contains(prieten)) {
                    set.add(prieten);
                    deVizitat.add(prieten);
                }
            }
        }
        return comunitate;
    }

}
