package com.mycompany.app;

import com.mycompany.actores.Espadachin;

/**
 * Hello world!
 *
 */
public class App 
{    
    private App() {}

    public static void main(String[] args) {
        akka.Main.main(new String[]{Espadachin.class.getName()});
    }
}
