package validator

import (
	"fmt"
	"os"
	"scene-keeper/internal/validator"
)

func Program() {
	if len(os.Args) < 2 {
		fmt.Println("Usage: scenekeeper <schema.json> <scene.json>")
		os.Exit(1)
	}

	schemaPath := os.Args[1]
	scenePath := os.Args[2]

	if err := validator.ValidateData(schemaPath, scenePath); err != nil {
		fmt.Println("scene invalid", err)
		os.Exit(1)
	}

	fmt.Println("scene valid")
}
