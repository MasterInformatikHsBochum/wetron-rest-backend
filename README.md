# WeTron REST Backend

## Compile in Docker-Container

docker build -t wetron-rest -f ./Dockerfile.build .

## Run App Locally

make run

## Build Docker-Container that contains our Rest-Binary

make builddocker

## Useful Docker Commands

Show running container: docker ps
Show running processes: docker top CONTAINER [ps OPTIONS]
