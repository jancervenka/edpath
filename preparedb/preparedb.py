import json
import sqlite3


def create_and_load():
    connection = sqlite3.connect('stars.db')
    print('Database opened!')

    q = 'DROP TABLE IF EXISTS stars;'

    connection.execute(q)

    q = 'CREATE TABLE stars (name TEXT, x REAL, y REAL, z REAL);'
    
    connection.execute(q)
    
    file = open('systems_coords.json')
    data = json.load(file)
    file.close()

    c = 0
    for key in data:
        name = key

        if "'" in name:
            name = name.replace("'", "''")

        x = data[key][0]
        y = data[key][0]
        z = data[key][0]
        q = """INSERT INTO stars (name, x, y, z) 
               VALUES ('{}', {}, {}, {});""".format(name, x, y, z)
        
        c += 1
        connection.execute(q)

    connection.commit()
    print('{} rows commited!'.format(c))

    connection.close()

if __name__ == '__main__':
    create_and_load()