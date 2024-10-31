import domain.Friendship;
import domain.Tuple;
import domain.Utilizator;
import domain.validators.*;
import repository.Repository;
import repository.file.UtilizatorRepository;
import repository.memory.InMemoryRepository;
import service.Service_Net;
import UI.UI;

public class Main {
    public static void main(String[] args) {
        ValidatorFactory factory = ValidatorFactory.getInstance();
        Validator userValidator = factory.createValidator(ValidatorStrategy.User);
        Validator friendValidator = factory.createValidator(ValidatorStrategy.Friendship);

        Repository<Integer, Utilizator> repoUser = new InMemoryRepository<Integer, Utilizator>(new UtilizatorValidator());
        Repository<Integer, Utilizator> repoUserFile = new UtilizatorRepository(new UtilizatorValidator(), "data/users.txt");

        Repository<Tuple<Integer, Integer>, Friendship> repoFriends = new InMemoryRepository<Tuple<Integer, Integer>, Friendship>(new FriendshipValidator());
        Service_Net service = new Service_Net(repoUserFile, repoFriends);

        UI ui = new UI(service);
        ui.showUI();
     }
}