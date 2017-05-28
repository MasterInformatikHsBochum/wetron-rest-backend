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
# get list of available sessions
curl 127.0.0.1:8080/sessions

# create a new session
curl -X POST 127.0.0.1:8080/session
```