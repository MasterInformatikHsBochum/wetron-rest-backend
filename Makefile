default: builddocker

buildgo:
    CGO_ENABLED=0 GOOS=linux go build -ldflags "-s" -a -installsuffix cgo -o main .

builddocker:
	docker build -t wetron-rest -f ./Dockerfile.build .

run:
	docker run -p 8080:8080 wetron-rest tail -f /dev/null