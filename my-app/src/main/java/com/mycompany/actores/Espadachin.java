package com.mycompany.actores;


import akka.actor.ActorRef;
import akka.actor.Props;
import akka.actor.UntypedAbstractActor;
import akka.event.Logging;
import akka.event.LoggingAdapter;

public class Espadachin extends UntypedAbstractActor {

    private final LoggingAdapter log = Logging.getLogger(getContext().system(), this);

    @Override
    public void preStart() {
        final ActorRef herrero = getContext().actorOf(Props.create(Herrero.class), "herrero");
        herrero.tell(Herrero.Mensaje.CREAR_ESPADA, getSelf());
    }

    @Override
    public void onReceive(Object o) {
        log.info("[Espadachin] ha recibido el mensaje: \"{}\".", o);
    }
}
