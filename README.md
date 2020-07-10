## Frontend

Serve the React front end

```sh
client/node_modules/serve/bin/serve.js client/build
```

## Backend

Open the USB0 port

```sh
stty -F /dev/ttyUSB0 -hupcl
```

Set the FLASK_APP variable

```sh
export FLASK_APP=./server/app.py
```

Run the backend
```sh
python3 -m flask run --host=0.0.0.0
```
