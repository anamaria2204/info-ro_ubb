package atelier.atelier_de_origami.observer;

import atelier.atelier_de_origami.events.Event;

public interface Observer<E extends Event> {
    void update(E e);

}
