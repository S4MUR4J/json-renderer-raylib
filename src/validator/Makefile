.PHONY: run test

data ?= null
schema ?= schema/scene.schema.json

run:
	go run . $(data) $(schema)

test:
	go test -v ./...

%:
	@:
