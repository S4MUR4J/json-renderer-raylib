.PHONY: run test

data ?= null
schema ?= schema/scene.schema.json

run:
	go run . $(data) $(schema)

lint:
	golangci-lint run

fmt:
	go fmt ./...
	go vet ./...

test:
	go test -v ./...

test-coverage:
	go test ./... -coverprofile=coverage.out
	go tool cover -html=coverage.out

%:
	@:
