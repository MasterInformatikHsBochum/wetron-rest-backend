# WeTron REST Backend

## Compile
```bash
mkdir -p build
cd build
cmake ..
make
```

## Test
```bash
./build/wetron-rest-backend
```

```bash
# Gets all sessions
curl 127.0.0.1:8080/sessions

# Creates a session
curl -X POST 127.0.0.1:8080/sessions

# Gets a session by id
curl -X GET 127.0.0.1:8080/sessions/68b329da9893e34099c7d8ad5cb9c940

# Joins a session
curl -X PUT 127.0.0.1:8080/sessions/68b329da9893e34099c7d8ad5cb9c940
```

## Protocol
| Method | Path | Description |
| ------ | ---- | ----------- |
| GET    | /sessions | Gets all sessions |
| POST   | /sessions | Creates a session |
| GET    | /sessions/{id} | Gets a session by id |
| PUT    | /sessions/{id} | Joins a session |
