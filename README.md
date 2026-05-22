# Shop-Inv — Inventory & Cashier System

Console-based inventory management and point-of-sale system written in C++17.

## Features
1. Product and category management (CRUD)
2. Inventory tracking with low stock alerts
3. Sales transactions with receipt generation
4. Discount system (percentage and fixed)
5. Transaction history with filtering
6. Supplier and delivery management
7. Reports and statistics
8. Barcode search and product filtering
9. User roles (admin/cashier) with access control
10. File-based data persistence

## Build & Run
```
make
./shop
```

## Default Users
- Admin: `Ivan` (role: admin)
- Cashier: `Maria` (role: cashier)

## File Structure
Each class has its own `.h` and `.cpp` file. Menu logic is separated in `MenuHelpers`. Data persists in `.txt` files.

## Class Hierarchy
- `Person` (abstract) → `Admin`, `Cashier`, `Supplier`
- `Product` (abstract) → `PhysicalProduct`, `ServiceProduct`
- `Discount` (abstract) → `PercentDiscount`, `FixedDiscount`
- `Transaction` ◆→ `TransactionItem`
- `Store` — central manager
- `AuthManager`, `FileManager`, `ReportManager`, `InputValidator`
