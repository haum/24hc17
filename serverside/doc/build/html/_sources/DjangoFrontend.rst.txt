DjangoFrontend
==============

Les URLs sont dans 3 zones :

- ``/api/user/``
- ``/api/team/``
- ``/api/propose_token/``

Les deux premières admettent plusieurs endpoints, la dernière est un endpoint final.
En cas d'échec, le serveur renvoie une erreur 500. Toutes les requêtes vers ``/api/``
renvoie une payload JSON.

/api/user/all
-------------

Renvoie une liste de tous les utilisateurs.

Réponse si aucun utilisateur :

.. code:: javascript

  {
    'command': 'get_all_users',
    'status': 'no user found',
    'result': []
  }

Réponse autrement :

.. code:: javascript

  {
    'command': 'get_all_users',
    'status': 'users found',
    'result': [
      {
        'pseudo': 'Leto',
        'primary': true,
        'team': {
          'name': 'Atreides',
          'location': 'Arakis',
          'score': 42
        }
      },
      {
        'pseudo': 'Rautha',
        'primary': true,
        'team': {
          'name': 'Harkonnen',
          'location': 'GeidiPrime',
          'score': 2
        }
      }
    ]
  }

/api/user/<username>
--------------------

Retourne les informations à propos de l'utilisateur ``<username>``. Le nom est validé
contre : ``[A-Za-z0-9\-_]``.

Le résultat si le nom demandé ne corresponde à aucun utilisateur est :

.. code:: javascript

  GET /api/user/Paul 404

  {
    'command': 'get_user',
    'status': 'unknown user',
    'result': []
  }

Réponse autrement :

.. code:: javascript

  GET /api/user/Leto 200

  {
    'command': 'get_user',
    'status': 'user found',
    'result': [
      {
        'pseudo': 'Leto',
        'primary': true,
        'team': {
          'name': 'Atreides',
          'location': 'Arakis',
          'score': 42
        }
      },
    ]
  }


/api/team/<teamname>/adduser/<username>
---------------------------------------

Ajoute l'utilisateur ``<username>`` à l'équipe ``<teamname>``. Si la team n'existe pas,
elle est créée à la volée, idem pour l'utilisateur. Si l'utilisateur existe et est
enregistré dans l'équipe demandée, l'endpoint retourne :

.. code:: javascript

  GET /api/team/Atreides/adduser/Leto 200

  {
    'command': 'register_user',
    'status': 'user already in team Atreides',
    'result': [
      {
        'pseudo': 'Leto',
        'primary': true,
        'team': {
          'name': 'Atreides',
          'location': 'Arakis',
          'score': 42
        }
      },
    ]
  }

Si l'utilisateur existe mais est enregistré dans une **autre équipe** :


.. code:: javascript

  GET /api/team/Atreides/adduser/Rautha 409

  {
    'command': 'register_user',
    'status': 'user already in another team (Harkonnen)',
    'result': [
      {
        'pseudo': 'Rautha',
        'primary': true,
        'team': {
          'name': 'Harkonnen',
          'location': 'GeidiPrime',
          'score': 2
        }
      },
    ]
  }

Sinon (avec une équipe existante):

.. code:: javascript

  GET /api/team/Atreides/adduser/Paul 200

  {
    'command': 'register_user',
    'status': 'user created',
    'result': [
      {
        'pseudo': 'Paul',
        'primary': true,
        'team': {
          'name': 'Atreides',
          'location': 'Arakis',
          'score': 42
        }
      },
    ]
  }

Sans équipe existante :

.. code:: javascript

  GET /api/team/Corrino/adduser/Duncan 200

  {
    'command': 'register_user',
    'status': 'user and team created',
    'result': [
      {
        'pseudo': 'Duncan',
        'primary': true,
        'team': {
          'name': 'Corrino',
          'location': 'Shaddam4',
          'score': 0
        }
      },
    ]
  }
