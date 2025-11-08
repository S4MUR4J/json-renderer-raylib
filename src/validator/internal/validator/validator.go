package validator

import (
	"fmt"
	"os"

	"github.com/santhosh-tekuri/jsonschema/v6"
)

func ValidateData(schemaPath string, dataFile string) error {
	compiler := jsonschema.NewCompiler()
	schema, err := compiler.Compile(schemaPath)
	if err != nil {
		return fmt.Errorf("compile schema %s: %w", schemaPath, err)
	}

	file, err := os.Open(dataFile)
	if err != nil {
		return fmt.Errorf("open data file %s: %w", dataFile, err)
	}
	defer file.Close()

	data, err := jsonschema.UnmarshalJSON(file)
	if err != nil {
		return fmt.Errorf("decode json from %s: %w", dataFile, err)
	}

	if err := schema.Validate(data); err != nil {
		return fmt.Errorf("validate %s with schema %s: %w", dataFile, schemaPath, err)
	}

	return nil
}
