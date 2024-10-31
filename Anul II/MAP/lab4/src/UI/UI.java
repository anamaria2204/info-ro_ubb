package UI;

import domain.Utilizator;
import service.Service_Net;

import java.util.List;
import java.util.Map;
import java.util.Objects;
import java.util.Scanner;
import java.util.concurrent.atomic.AtomicInteger;

public class UI {
    private final Service_Net service;
    private Scanner scanner;

    public UI(Service_Net service) {
        this.service = service;
        scanner = new Scanner(System.in);
    }

    public void printMenu(){
        System.out.println("1. Adauga utilizator");
        System.out.println("2. Adauga prietenie intre doi utilizatori");
        System.out.println("3. Sterge utilizator");
        System.out.println("4. Sterge prietenie");
        System.out.println("5. Afiseaza toti utilizatorii");
        System.out.println("6. Afiseaza toate prieteniile");
        System.out.println("7. Afiseaza toate comunitatiile");
        System.out.println("8. Afiseaza cea mai mare comunitate");
        System.out.println("0. Exit");
    }

    private void addUserPrompt(){
        System.out.println("Introduceti numele: ");
        String lastName = scanner.nextLine();
        System.out.println("Introduceti prenumele: ");
        String firstName = scanner.nextLine();
        System.out.println("Introduceti username-ul: ");
        String username = scanner.nextLine();

        service.addUser(lastName, firstName, username);

        System.out.println("Utilizator adaugat cu succes!\n");

        getAllUtilizatoriPrompt();
    }

    private void addFrienshipPrompt(){
        System.out.println("Introduceti username-ul primului utilizator: ");
        String username1 = scanner.nextLine();
        System.out.println("Introduceti username-ul celui de-al doilea utilizator: ");
        String username2 = scanner.nextLine();

        service.addFriendship(username1, username2);

        System.out.println("Prietenie realizata cu succes!\n");

        getAllPrieteniePrompt();
    }

    private void removeUserPrompt(){
       System.out.println("Introduceti username-ul: ");
       String username = scanner.nextLine();
       service.removeUser(username);
       System.out.println("Utilizator sters cu succes!\n");

       getAllUtilizatoriPrompt();
    }

    private void removeFrienshipPrompt(){
        System.out.println("Introduceti username-ul primului user: ");
        String username1 = scanner.nextLine();
        System.out.println("Introduceti username-ul celui de-al doilea user: ");
        String username2 = scanner.nextLine();

        service.removeFriendship(username1, username2);
        System.out.println("Prietenie stearsa cu succes!\n");

        getAllPrieteniePrompt();
    }

    private void getAllUtilizatoriPrompt(){
        System.out.println("Toti utilizatorii: \n");
        service.getAllUsers().forEach(System.out::println);
        System.out.println();
    }

    private void getAllPrieteniePrompt(){
        System.out.println("Toate prieteniile: \n");
        service.getAllFriendships().forEach(System.out::println);
        System.out.println();
    }

    private void showAllComunitiesPrompt(){
        Map<String, Object> rezultat = service.showNumberofComunities();
        AtomicInteger nrComunitati = (AtomicInteger) rezultat.get("Numarul de comunitati");

        int numar = nrComunitati.get();

        System.out.println("Numarul de comunitati este: " + numar + "\n");

        List<List<Utilizator>> comunitati = (List<List<Utilizator>> ) rezultat.get("Comunitati");

        // Print each community and its members
        for (int i = 0; i < comunitati.size(); i++) {
            System.out.println("Communitatea " + (i + 1) + ":");
            for (Utilizator member : comunitati.get(i)) {
                System.out.println(" - " + member);
            }
            System.out.println();
        }

    }

    private void biggestComunityprompt(){
        List<Utilizator> biggest = service.biggestCommunity();
        System.out.println("Cea mai sociabila comunitate: " );
        for(Utilizator u: biggest){
            System.out.println(u);
        }
        System.out.println();

    }

    private void addFriendships(){
        service.addFriendship("anamaria_ordean", "deea307");
        service.addFriendship("anamaria_ordean", "thedanoprean");
        service.addFriendship("anamaria_ordean", "thepaulroman");
        service.addFriendship("deea307", "thedanoprean");
        service.addFriendship("deea307", "thepaulroman");
        service.addFriendship("deea307", "cristi_oprean");

        service.addFriendship("maria.oprean", "dorina_muntean");
    }

    public void showUI(){
        addFriendships();
        while(true){
            printMenu();
            System.out.println("\n Introduceti optiunea dorita: ");
            String option = scanner.nextLine();
            if(option.equals("0")) {
                System.out.println("La revedere!\n");
                break;
            }
            else if(option.equals("1")) {
                addUserPrompt();
            }
            else if(option.equals("2")) {
                addFrienshipPrompt();
            }
            else if(option.equals("3")) {
                removeUserPrompt();
            }
            else if(option.equals("4")) {
                removeFrienshipPrompt();
            }
            else if(option.equals("5")) {
                getAllUtilizatoriPrompt();
            }
            else if(option.equals("6")) {
                getAllPrieteniePrompt();
            }
            else if(option.equals("7")) {
                showAllComunitiesPrompt();
            }
            else if(option.equals("8")){
                biggestComunityprompt();
            }
        }
    }
}
