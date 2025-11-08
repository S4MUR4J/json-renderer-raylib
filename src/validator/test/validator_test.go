package validator_test 

import (
	"scene-keeper/internal/validator"
	"testing"
)

func TestValidateData(t *testing.T) {
	tests := []struct {
		name       string
		schema     string
		data       string
		shouldFail bool
	}{
		{"valid scene", "../../schema/scene.schema.json", "../../examples/valid_scene.json", false},
		{"empty scene", "../../schema/scene.schema.json", "../../examples/empty_scene.json", false},
		{"invalid scene", "../../schema/scene.schema.json", "../../examples/invalid_scene.json", true},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			err := validator.ValidateData(tt.schema, tt.data)
			if (err != nil) != tt.shouldFail {
				t.Errorf("expected error=%v, got %v", tt.shouldFail, err)
			}
		})
	}
}
