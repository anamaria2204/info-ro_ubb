package atelier.atelier_de_origami.repository;
import java.util.Optional;

public interface IRepository<ID,E> {
    Optional findOne(ID id);
    Iterable<E> findAll();
}
